using System;
using System.Collections.Generic;
using UnityEngine;

public class ObserverTracker<T> : IObservable<T>
{
    private List<IObserver<T>> observers;

    public ObserverTracker() {
        observers = new List<IObserver<T>>();
    }

    public IDisposable Subscribe(IObserver<T> observer) {
        observers.Add(observer);

        return new UnSubscriber<T>(observers, observer);
    }

    public void Unsubscribe(IObserver<T> observer) {
        new UnSubscriber<T>(observers, observer).Dispose();
    }

    public void Update(T data) {
        for (int i = 0; i < observers.Count; i++) {
            try {
                observers[i].OnNext(data);
            }
            catch (Exception e) {
                observers[i].OnError(e);
            }
        }
    }

    public void Notify() {
        for (int i = 0; i < observers.Count; i++) {
            try {
                observers[i].OnCompleted();
            }
            catch (Exception e) {
                observers[i].OnError(e);
            }
        }
    }
}