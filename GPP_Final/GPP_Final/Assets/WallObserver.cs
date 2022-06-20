using System;
using UnityEngine;

internal class WallObserver : IObserver<WallActionType> {
    private GameObject wallObject;
    private int wallHP;

    private WallActionType nextAction;
    private Action action;

    public WallObserver(GameObject wallObject) {
        this.wallObject = wallObject;
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
            default:
                break;
        }
    }

    private void Destroy() {
        Debug.Log("Destroy");
        GameObject.Destroy(wallObject);
    }
}