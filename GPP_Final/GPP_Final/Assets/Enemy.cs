using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {
    public Transform player;
    float shootTime;
    float roarTime;

    private void Start() {
        if (player == null)
            player = GameObject.Find("Player").transform;
    }

    // Update is called once per frame
    void FixedUpdate() {
        transform.position = Vector3.MoveTowards(transform.position, player.position, Time.deltaTime);
        transform.LookAt(player);

        shootTime += Time.deltaTime;
        roarTime += Time.deltaTime;

        if (shootTime > 3f) {
            Shoot();
            shootTime = 0;
        }

        if (roarTime > 8f) {
            Roar();
            roarTime = 0;
        }
    }

    void Shoot() {
        var bullet = GameObject.CreatePrimitive(PrimitiveType.Sphere);
        bullet.transform.localScale /= 2;
        bullet.transform.position = transform.position;
        bullet.GetComponent<MeshRenderer>().material.color = Color.black;
        bullet.layer = LayerMask.NameToLayer("Bullet");
        var rigid = bullet.AddComponent<Rigidbody>();
        rigid.useGravity = false;
        rigid.AddForce(transform.forward, ForceMode.Force);
        rigid.velocity = transform.forward * 5;
        Destroy(bullet, 5f);
    }

    void Roar() {
        ObserverHandler.GetInstance().wallOberverTracker.Update(WallActionType.Corrosion);
        ObserverHandler.GetInstance().wallOberverTracker.Notify();
    }
}
