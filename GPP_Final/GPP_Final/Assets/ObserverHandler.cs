using System;
using System.Collections.Generic;
using UnityEngine;

internal class ObserverHandler
{
    // Singleton
    private static ObserverHandler instance;

    private ObserverHandler() {
        wallOberverTracker = new ObserverTracker<WallActionType>();
    }

    public static ObserverHandler GetInstance() {
        if (instance == null) {
            instance = new ObserverHandler();
            if (instance == null)
                instance = Activator.CreateInstance<ObserverHandler>();
        }

        return instance;
    }

    public ObserverTracker<WallActionType> wallOberverTracker;
}
