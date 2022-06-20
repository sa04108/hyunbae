using System;
using UnityEngine;

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

    }

    public void OnNext(WallActionType value) { // 행동 데이터 받기
        nextAction = value;

        switch (value) {
            case WallActionType.Destroy:
                action = Destroy;
                break;
            case WallActionType.ChangeColor:
                action = ChangeColor;
                break;
            default:
                break;
        }
    }

    private void Destroy() {
        Destroy(gameObject);
    }

    private void ChangeColor() {
        GetComponent<MeshRenderer>().material.color = Color.black;
    }

    public void UnSubscribe() {
        Destroy(gameObject);
        ObserverHandler.GetInstance().wallOberverTracker.Unsubscribe(this);
    }

    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.layer == 8) {
            Destroy(collision.gameObject);
            Destroy();
        }
    }
}