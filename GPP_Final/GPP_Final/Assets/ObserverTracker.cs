using System;
using System.Collections.Generic;
using UnityEngine;

public class ObserverTracker<T> : IObservable<T>
{
    private List<IObserver<T>> observers;
    private IDisposable unsubscriber;

    public ObserverTracker() {
        observers = new List<IObserver<T>>();
    }

    public IDisposable Subscribe(IObserver<T> observer) {
        if (unsubscriber == null)
            unsubscriber = new UnSubscriber<T>(observers, observer);

        observers.Add(observer);

        return unsubscriber;
    }

    public void Unsubscribe(IObserver<T> observer) {
        unsubscriber?.Dispose();
    }

    public void Update(T data) {
        foreach (var observer in observers) {
            observer.OnNext(data);
        }
    }

    public void Notify() {
        foreach (var observer in observers) {
            observer.OnCompleted();
        }
    }
}