#include "BaseGame.h"

#include "Header.h"
BaseGame::BaseGame(Graphic* graphic)
	:bGraphic(graphic)
{
	graphic->renderDelegate->AddFunction<BaseGame>(this,&BaseGame::Render);
}
BaseGame::~BaseGame()
{
	bGraphic->renderDelegate->RemoveFunction<BaseGame>(this,&BaseGame::Render);
}