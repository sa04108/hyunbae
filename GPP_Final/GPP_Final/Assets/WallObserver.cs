using System;
using UnityEngine;

public enum WallActionType {
    Corrosion,
    Destroy
}

internal class WallObserver : MonoBehaviour, IObserver<WallActionType> {
    private Action action;
    private int wallHp;

    void Start() {
        wallHp = 2;
    }

    public void Subscribe() {
        ObserverHandler.GetInstance().wallOberverTracker.Subscribe(this);
    }

    public void OnCompleted() { // 데이터를 받은 후 행동
        action?.Invoke();
    }

    public void OnError(Exception error) {
        Debug.LogWarning(error.Message);
    }

    public void OnNext(WallActionType value) { // 행동 데이터 받기
        switch (value) {
            case WallActionType.Corrosion:
                action = Corrosion;
                break;
            case WallActionType.Destroy:
                action = UnSubscribe;
                break;
            default:
                break;
        }
    }

    private void Corrosion() {
        wallHp--;
        GetComponent<MeshRenderer>().material.color = Color.black;

    }

    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.layer == LayerMask.NameToLayer("Bullet")) {
            wallHp--;
            GetComponent<MeshRenderer>().material.color = Color.black;

            if (wallHp <= 0) {
                Destroy(collision.gameObject);
                UnSubscribe();
            }
        }
    }

    public void UnSubscribe() {
        ObserverHandler.GetInstance().wallOberverTracker.Unsubscribe(this);
        Destroy(gameObject);
    }
}