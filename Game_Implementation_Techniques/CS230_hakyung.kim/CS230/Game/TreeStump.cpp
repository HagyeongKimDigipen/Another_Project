#include "../Engine/TransformMatrix.h"
#include "Level1.h"
#include "TreeStump.h"

TreeStump::TreeStump(Vector2D pos, int size) : GameObject(pos) {
	switch (size) {
	case 1:
		sprite.Load("assets/treeStump1.spt", this);
		break;
	case 2:
		sprite.Load("assets/treeStump2.spt", this);
		break;
	case 3:
		sprite.Load("assets/treeStump3.spt", this);
		break;
	case 5:
		sprite.Load("assets/treeStump5.spt", this);
		break;
	}
}