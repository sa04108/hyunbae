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
        foreach (var observer in observers) {
            try {
                observer.OnNext(data);
            }
            catch (Exception e) {
                observer.OnError(e);
            }
        }
    }

    public void Notify() {
        foreach (var observer in observers) {
            try {
                observer.OnCompleted();
            }
            catch (Exception e) {
                observer.OnError(e);
            }
        }
    }
}