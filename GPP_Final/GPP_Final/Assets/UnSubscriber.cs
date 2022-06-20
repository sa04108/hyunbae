using System;
using System.Collections.Generic;

internal class UnSubscriber<T> : IDisposable {
    private List<IObserver<T>> observers;
    private IObserver<T> observer;

    public UnSubscriber(List<IObserver<T>> observers, IObserver<T> observer) {
        this.observers = observers;
        this.observer = observer;
    }

    public void Dispose() {
        if (observers.Contains(observer))
            observers.Remove(observer);
    }
}