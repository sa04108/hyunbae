using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {
    public Transform player;

    private void Start() {
        if (player == null)
            player = GameObject.Find("Player").transform;
    }

    // Update is called once per frame
    void Update() {
        transform.position = Vector3.MoveTowards(transform.position, player.position, Time.deltaTime);
    }
}
