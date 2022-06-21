using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    public int playerHP;
    private Coroutine damagedCoroutine;

    private void OnCollisionEnter(Collision collision) {
        if (collision.gameObject.layer == LayerMask.NameToLayer("Bullet")) {
            Destroy(collision.gameObject);

            if (damagedCoroutine != null)
                StopCoroutine(damagedCoroutine);
            damagedCoroutine = StartCoroutine(Damaged());
            playerHP--;

            if (playerHP <= 0) {
                ObserverHandler.GetInstance().wallOberverTracker.Update(WallActionType.Destroy);
                ObserverHandler.GetInstance().wallOberverTracker.Notify();
                gameObject.SetActive(false);
            }
        }
            
    }

    IEnumerator Damaged() {
        GetComponent<MeshRenderer>().material.color = Color.yellow;
        yield return new WaitForSeconds(0.5f);
        GetComponent<MeshRenderer>().material.color = Color.white;
    }
}
