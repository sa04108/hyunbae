using System;
using UnityEngine;

public enum WallActionType {
    ChangeColor
}

internal class WallObserver : MonoBehaviour, IObserver<WallActionType> {
    private int wallHP;

    private WallActionType nextAction;
    private Action action;

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
        nextAction = value;

        switch (value) {
            case WallActionType.ChangeColor:
                action = ChangeColor;
                break;
            default:
                break;
        }
    }

    private void ChangeColor() {
        GetComponent<MeshRenderer>().material.color = Color.black;
    }

    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.layer == LayerMask.NameToLayer("Bullet")) {
            Destroy(collision.gameObject);
            UnSubscribe();
        }
    }

    public void UnSubscribe() {
        ObserverHandler.GetInstance().wallOberverTracker.Unsubscribe(this);
        Destroy(gameObject);
    }
}