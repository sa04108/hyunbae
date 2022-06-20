using System;
using System.Collections.Generic;
using UnityEngine;

public enum WallActionType {
    Destroy
}

//The parent class
public abstract class Command {
    public Command() { }

    public abstract void Execute();

    public virtual void Move() { }
    public virtual void Undo() { }

    protected void push() {
        InputHandler.oldCommands.Add(this);
    }

}


//
// Child classes
//

public class CreateWallCommand : Command {
    Vector3 hitPos;
    public CreateWallCommand(Vector3 mouseHit) {
        hitPos = mouseHit;
    }

    public override void Execute() {
        var wall = GameObject.CreatePrimitive(PrimitiveType.Cube);
        wall.GetComponent<MeshRenderer>().material.color = Color.yellow;
        wall.tag = "Wall";
        wall.transform.position = GridManager.pos2center(hitPos);

        GridManager.SetAsWall(wall.transform.position);

        WallObserver wallOberver = new WallObserver(wall);
        ObserverHandler.disposableObervers.Add(ObserverHandler.wallOberverTracker.Subscribe(wallOberver));
        push();
    }
}

public class DestroyWallCommand : Command {
    Transform subject;
    public DestroyWallCommand(Transform hitObject) {
        subject = hitObject;
    }

    public override void Execute() {
        GridManager.SetAsNotWall(subject.position);

        ObserverHandler.wallOberverTracker.Update(WallActionType.Destroy);
        ObserverHandler.wallOberverTracker.Notify();
        push();
    }
}

public class MoveCommand : Command {
    Transform subject;
    Vector3 prevPos;
    Vector3 nextPos;

    public MoveCommand(Transform subject, Vector3 prevPos, Vector3 nextPos) {
        this.subject = subject;
        this.prevPos = prevPos;
        this.nextPos = nextPos;
    }

    public override void Execute() {
        Move();
        push();
    }

    public override void Move() {
        subject.position = nextPos;
        GridManager.drawRect(GridManager.pos2Cell(subject.position), Color.red, Time.deltaTime);
    }

    public override void Undo() {
        subject.position = prevPos;
        GridManager.drawRect(GridManager.pos2Cell(subject.position), Color.red, Time.deltaTime);
    }
}

public class UndoCommand : Command {
    public UndoCommand() { }

    public override void Execute() {
        List<Command> oldCommands = InputHandler.oldCommands;

        if (oldCommands.Count == 0) return;

        Command latestCommand = oldCommands[oldCommands.Count - 1];

        latestCommand.Undo();

        oldCommands.RemoveAt(oldCommands.Count - 1);

        //InputHandler.moveIndex--;
    }
}

public class ReplayCommand : Command {
    public ReplayCommand() { }

    public override void Execute() {
        InputHandler.shouldStartReplay = true;
    }
}

public class DoNothing : Command {
    public DoNothing() { }

    public override void Execute() {
        push();
    }
}