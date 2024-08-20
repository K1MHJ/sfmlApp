#include "bot.h"

void Bot::Init()
{
  gameOver = false;
}
void Bot::OnUpdate(Timestep ts)
{

}
void Bot::OnRender()
{

}
void Bot::Reset()
{

}
void Bot::GameOver()
{
  gameOver = true;
}
int Bot::Order(const Grid& _grid, Block& _curBlock, const Block& _nextBlock)
{
  if (!gameOver) {
    return 1;
  }
}
