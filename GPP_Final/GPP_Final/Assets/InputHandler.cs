using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class InputHandler : MonoBehaviour {
    // Singleton
    private static InputHandler instance;

    public static InputHandler GetInstance() {
        if (instance == null)
            instance = FindObjectOfType(typeof(InputHandler)) as InputHandler;

        return instance;
    }

    public Transform player;
    public Transform playerFuture;

    private GridManager gridManager;
    private GameObject endPoint;

    public List<Command> oldCommands = new List<Command>();

    private Coroutine replayCoroutine;
    private bool isMoving;
    private bool isReplaying;

    private void Awake() {
        instance = this;
    }

    void Start() {
        playerFuture.position = player.position;
        gridManager = Camera.main.GetComponent<GridManager>();
        if (player == null) player = GameObject.Find("Player").transform;
    }

    void Update() {
        player.position = Vector3.MoveTowards(player.position, playerFuture.position, Time.deltaTime * 5f);

        if (!isMoving && !isReplaying)
            HandleInput();
    }


    public void HandleInput() {
        if (Input.GetKeyDown(KeyCode.U)) {
            UndoCommand undoCommand = new UndoCommand(player.position);
            undoCommand.Execute();
        }
        else if (Input.GetKeyDown(KeyCode.R)) {
            ReplayCommand replayCommand = new ReplayCommand(player.position);
            replayCommand.Execute();
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

                    var pathVec3 = gridManager.GetPathVector3(hit.point);
                    MoveCommand moveCommand = new MoveCommand(pathVec3, player.position);
                    moveCommand.Execute();
                }
            }
        }
        else if (Input.GetMouseButtonDown(1)) {
            var ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            RaycastHit hit;
            if (Physics.Raycast(ray, out hit)) {
                if (hit.transform.tag == "Plane") {
                    CreateWallCommand createWallCommand = new CreateWallCommand(player.position, hit.point);
                    createWallCommand.Execute();
                }
                else if (hit.transform.tag == "Wall") {
                    DestroyWallCommand destroyWallCommand = new DestroyWallCommand(player.position, hit.transform);
                    destroyWallCommand.Execute();
                }
            }
        }
    }

    public void MoveByPath(List<Vector3> path) {
        StartCoroutine(MoveCoroutine(path));
    }

    IEnumerator MoveCoroutine(List<Vector3> path) {
        isMoving = true;

        if (path == null) yield break;

        foreach (var pos in path) {
            GridManager.drawRect(GridManager.pos2Cell(player.position), Color.red, Time.deltaTime);

            playerFuture.position = pos;
            yield return new WaitForSeconds(0.2f);
        }

        isMoving = false;
    }

    //Checks if we should start the replay
    public void StartReplay() {
        if (oldCommands.Count > 0) {
            if (replayCoroutine != null) {
                StopCoroutine(replayCoroutine);
            }

            replayCoroutine = StartCoroutine(ReplayCommands());
        }
    }

    //The replay coroutine
    IEnumerator ReplayCommands() {
        isReplaying = true;

        Time.timeScale = 2;

        player.position = oldCommands[0].currentPos;

        for (int i = 0; i < oldCommands.Count; i++) {
            oldCommands[i].Execute();

            yield return new WaitWhile(() => isMoving);

            yield return new WaitForSeconds(0.5f);
        }

        isReplaying = false;
        Time.timeScale = 1;
    }
}
