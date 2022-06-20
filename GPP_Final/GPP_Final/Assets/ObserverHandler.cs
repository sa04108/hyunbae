using System;
using System.Collections.Generic;

internal static class ObserverHandler
{
    static ObserverHandler() {
        wallOberverTracker = new ObserverTracker<WallActionType>();
        disposableObervers = new List<IDisposable>();
    }

    public static ObserverTracker<WallActionType> wallOberverTracker;
    public static List<IDisposable> disposableObervers;
}
