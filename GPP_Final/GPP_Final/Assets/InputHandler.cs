using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class InputHandler : MonoBehaviour {
    public Transform player;
    public Transform playerFuture;
    private Vector3 startPos;

    private GridManager gridManager;
    private List<Vector3> pathVec3;
    private GameObject endPoint;

    private Command buttonU;
    private Command buttonR;
    private Command buttonN;

    public static List<Command> oldCommands = new List<Command>();
    public static bool shouldStartReplay;

    private Coroutine replayCoroutine;
    private bool isReplaying;

    Dictionary<KeyCode, Command> basicButtons;

    void Start() {
        playerFuture.position = player.position;
        gridManager = Camera.main.GetComponent<GridManager>();
        if (player == null) player = GameObject.Find("Player").transform;

        startPos = player.position;

        buttonU = new UndoCommand();
        buttonR = new ReplayCommand();
        buttonN = new DoNothing();

        basicButtons = new Dictionary<KeyCode, Command>() {
                        { KeyCode.U, buttonU },
                        { KeyCode.R, buttonR },
                        { KeyCode.N, buttonN }
        };
    }

    void Update() {
        player.position = Vector3.MoveTowards(player.position, playerFuture.position, Time.deltaTime * 5f);

        if (!isReplaying)
            HandleInput();

        StartReplay();
    }


    public void HandleInput() {
        foreach (var kv in basicButtons) {
            if (Input.GetKeyDown(kv.Key))
                kv.Value.Execute();
        }

        if (Input.GetMouseButtonDown(0)) {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit)) {
                //if (hit.transform.tag == "Wall" && hit.normal == Vector3.up) {
                //    var wall = GameObject.CreatePrimitive(PrimitiveType.Cube);
                //    wall.GetComponent<MeshRenderer>().material.color = Color.yellow;
                //    wall.tag = "Wall";
                //    wall.transform.position = hit.transform.position + Vector3.up;
                //    return;
                //}
                if (hit.transform.tag == "Plane") {
                    if (endPoint != null)
                        Destroy(endPoint);
                    endPoint = GameObject.CreatePrimitive(PrimitiveType.Plane);
                    endPoint.GetComponent<MeshRenderer>().material.color = Color.blue;
                    endPoint.transform.localScale = Vector3.one * 0.1f;
                    endPoint.tag = "Plane";
                    endPoint.transform.position = GridManager.pos2center(hit.point) + Vector3.down * 0.49f;

                    startPos = player.position;
                    pathVec3 = gridManager.GetPathVector3(hit.point);
                    StartCoroutine(MoveCommands(SetMoveCommands(pathVec3)));
                }
            }
        }
        else if (Input.GetMouseButtonDown(1)) {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit)) {
                if (hit.transform.tag == "Plane") {
                    CreateWallCommand createWallCommand = new CreateWallCommand(hit.point);
                    createWallCommand.Execute();
                }
                else if (hit.transform.tag == "Wall") {
                    DestroyWallCommand destroyWallCommand = new DestroyWallCommand(hit.transform);
                    destroyWallCommand.Execute();
                }
            }
        }
    }

    //Checks if we should start the replay
    void StartReplay() {
        if (shouldStartReplay && oldCommands.Count > 0) {
            shouldStartReplay = false;

            if (replayCoroutine != null) {
                StopCoroutine(replayCoroutine);
            }

            replayCoroutine = StartCoroutine(ReplayCommands());
        }
    }

    List<Command> SetMoveCommands(List<Vector3> paths) {
        List<Command> commandList = new List<Command>();
        commandList.Add(new MoveCommand(playerFuture, startPos, pathVec3[0]));

        for (int i = 1; i < pathVec3.Count; i++) {
            Command moveCommand = new MoveCommand(playerFuture, pathVec3[i - 1], pathVec3[i]);
            commandList.Add(moveCommand);
        }

        return commandList;
    }

    IEnumerator MoveCommands(List<Command> commands) {
        while (commands.Count > 0) {
            commands[0].Execute();
            commands.RemoveAt(0);

            yield return new WaitForSeconds(0.2f);
        }
    }

    //The replay coroutine
    IEnumerator ReplayCommands() {
        isReplaying = true;

        Time.timeScale = 2;

        player.position = startPos;

        for (int i = 0; i < oldCommands.Count; i++) {
            oldCommands[i].Move();

            yield return new WaitForSeconds(0.1f);
        }

        isReplaying = false;
        Time.timeScale = 1;
    }
}
