#include "Animation.h"
Animation::Animation()
{
	speedTextureChange = 0;
	animateCount = 0;
	//path = new std::vector<std::string>();
	loader = new Loader();
}
Animation::Animation(std::vector<std::string> path_)
{
	speedTextureChange = 0;
	animateCount = 0;
	path = path_;
	loader = new Loader();
	for (int i = 0; i < path.size(); i++)
	{
		loader->LoadImage(reinterpret_cast<const ILstring>(path[i].c_str()),path[i]);

		loader->image->TextureCoordinats[loader->CountIndexTexture - 1][0] = 1.f;
		loader->image->TextureCoordinats[loader->CountIndexTexture - 1][1] = .0f;
		loader->image->TextureCoordinats[loader->CountIndexTexture - 1][2] = 1.f;
		loader->image->TextureCoordinats[loader->CountIndexTexture - 1][3] = .0f;

		loader->image->VertexCoordinats[loader->CountIndexTexture - 1][0] = 1.f;
		loader->image->VertexCoordinats[loader->CountIndexTexture - 1][1] = .2f;
		loader->image->VertexCoordinats[loader->CountIndexTexture - 1][2] = -.2f;
		loader->image->VertexCoordinats[loader->CountIndexTexture - 1][3] = -1.f;

	}
}
void Animation::ShowAnimation()
{
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glAlphaFunc(GL_GREATER, 0.0f);

	if (speedTextureChange > 100 && speedTextureChange < 200 && animateCount == 0)
		animateCount++;
	if (speedTextureChange > 200 && speedTextureChange < 300 && animateCount == 1)
		animateCount++;
	if (speedTextureChange > 300 && speedTextureChange < 400 && animateCount == 2)
		animateCount++;
	if (speedTextureChange > 400 && speedTextureChange < 500 && animateCount == 3)
		animateCount++;
	if (speedTextureChange > 500 && speedTextureChange < 600 && animateCount == 4)
		animateCount++;
	if (speedTextureChange > 600 && speedTextureChange < 700 && animateCount == 5)
		animateCount++;
	if (speedTextureChange > 700 && speedTextureChange < 800 && animateCount == 6)
		animateCount++;
	if (speedTextureChange > 800 && speedTextureChange < 900 && animateCount == 7)
		animateCount++;
	if (speedTextureChange > 900 && speedTextureChange < 1000 && animateCount == 8)
		animateCount++;
	if (speedTextureChange > 1000 && speedTextureChange < 1100 && animateCount == 9)
		animateCount++;
	if (speedTextureChange > 1100 && speedTextureChange < 1200 && animateCount == 10)
		animateCount++;
	if (speedTextureChange > 1200 && speedTextureChange < 1300 && animateCount == 11)
		animateCount++;
	if (animateCount == path.size())
	{
		animateCount = 0;
		speedTextureChange = 0;
	}
	int numTexture = loader->FindTexture(path[animateCount]);
	glBindTexture(GL_TEXTURE_2D, loader->image->IndexTexture[numTexture]);
	EnableTexture(numTexture);
	speedTextureChange+=5;

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
};
void Animation::EnableTexture(int animboom)
{
	glBegin(GL_QUADS);
	glTexCoord2f(loader->image->TextureCoordinats[animboom][0], loader->image->TextureCoordinats[animboom][2]);
	glVertex2f(loader->image->VertexCoordinats[animboom][0], loader->image->VertexCoordinats[animboom][2]);

	glTexCoord2f(loader->image->TextureCoordinats[animboom][1], loader->image->TextureCoordinats[animboom][2]);
	glVertex2f(loader->image->VertexCoordinats[animboom][1], loader->image->VertexCoordinats[animboom][2]);

	glTexCoord2f(loader->image->TextureCoordinats[animboom][1], loader->image->TextureCoordinats[animboom][3]);
	glVertex2f(loader->image->VertexCoordinats[animboom][1], loader->image->VertexCoordinats[animboom][3]);

	glTexCoord2f(loader->image->TextureCoordinats[animboom][0], loader->image->TextureCoordinats[animboom][3]);
	glVertex2f(loader->image->VertexCoordinats[animboom][0], loader->image->VertexCoordinats[animboom][3]);
	glEnd();
}
Animation::~Animation()
{
	loader->~Loader();
	path.clear();
}
