using System;
using System.Collections.Generic;
using UnityEngine;

//The parent class
public abstract class Command {
    public readonly Vector3 currentPos;

    public Command(Vector3 currentPos) {
        this.currentPos = currentPos;
    }

    public abstract void Execute();

    public virtual void Move() { }
    public virtual void Undo() { }

    protected void push() {
        InputHandler.GetInstance().oldCommands.Add(this);
    }

}


//
// Child classes
//

public class CreateWallCommand : Command {
    WallObserver wallOberver;
    Vector3 hitPos;
    Vector3 wallPos;

    public CreateWallCommand(Vector3 currentPos, Vector3 mouseHit) : base(currentPos) {
        hitPos = mouseHit;
    }

    public override void Execute() {
        Move();
        push();
    }

    public override void Move() {
        var wall = GameObject.CreatePrimitive(PrimitiveType.Cube);
        wall.GetComponent<MeshRenderer>().material.color = Color.yellow;
        wall.tag = "Wall";
        wallPos = GridManager.pos2center(hitPos);
        wall.transform.position = wallPos;

        wallOberver = wall.AddComponent<WallObserver>();
        wallOberver.Subscribe();

        GridManager.SetAsWall(wall.transform.position);
    }

    public override void Undo() {
        if (wallOberver != null) {
            GridManager.SetAsNotWall(wallOberver.transform.position);

            wallOberver.UnSubscribe();
        }
        else if (wallPos != null) {
            GridManager.SetAsNotWall(wallPos);

            foreach (var wallObject in GameObject.FindGameObjectsWithTag("Wall")) {
                if (wallObject.transform.position == wallPos)
                    wallObject.GetComponent<WallObserver>().UnSubscribe();
            }
        }
    }
}

public class DestroyWallCommand : Command {
    Transform wallTransform;
    Vector3 hitPos;
    public DestroyWallCommand(Vector3 currentPos, Transform hitObject) : base(currentPos) {
        wallTransform = hitObject;
        hitPos = wallTransform.position;
    }

    public override void Execute() {
        Move();
        push();
    }

    public override void Move() {
        if (wallTransform != null) {
            GridManager.SetAsNotWall(wallTransform.position);

            wallTransform.GetComponent<WallObserver>().UnSubscribe();
        }
        else if (hitPos != null) {
            GridManager.SetAsNotWall(hitPos);

            foreach (var wallObject in GameObject.FindGameObjectsWithTag("Wall")) {
                if (wallObject.transform.position == hitPos)
                    wallObject.GetComponent<WallObserver>().UnSubscribe();
            }
        }
    }

    public override void Undo() {
        if (hitPos != null) { // subject의 Transform은 얕게 복사되어서 원본이 사라지면 같이 사라짐
            var wall = GameObject.CreatePrimitive(PrimitiveType.Cube);
            wall.GetComponent<MeshRenderer>().material.color = Color.yellow;
            wall.tag = "Wall";
            wall.transform.position = GridManager.pos2center(hitPos);

            WallObserver wallOberver = wall.AddComponent<WallObserver>();
            wallOberver.Subscribe();

            GridManager.SetAsWall(wall.transform.position);
        }
    }
}

public class MoveCommand : Command {
    List<Vector3> path;

    public MoveCommand(List<Vector3> path, Vector3 currentPos) : base(currentPos) {
        this.path = path;
    }

    public override void Execute() {
        Move();
        push();
    }

    public override void Move() {
        InputHandler.GetInstance().MoveByPath(path);
    }

    public override void Undo() {
        List<Vector3> reversed = path.ConvertAll(v => new Vector3(v.x, v.y, v.z));
        reversed.Reverse();
        reversed.RemoveAt(0);
        reversed.Add(currentPos);
        InputHandler.GetInstance().MoveByPath(reversed);
    }
}

public class UndoCommand : Command {
    public UndoCommand(Vector3 currentPos) : base(currentPos) { }

    public override void Execute() {
        List<Command> oldCommands = InputHandler.GetInstance().oldCommands;

        if (oldCommands.Count == 0) return;

        Command latestCommand = oldCommands[oldCommands.Count - 1];

        latestCommand.Undo();

        oldCommands.RemoveAt(oldCommands.Count - 1);
    }
}

public class ReplayCommand : Command {
    public ReplayCommand(Vector3 currentPos) : base(currentPos) { }

    public override void Execute() {
        InputHandler.GetInstance().StartReplay();
    }
}

public class DoNothing : Command {
    public DoNothing(Vector3 currentPos) : base(currentPos) { }

    public override void Execute() {
        push();
    }
}