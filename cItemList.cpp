#include "cItemList.h"

cItemList::cItemList()
{
	items.clear();
}

cItemList::cItemList(const char *fn)
{
	items.clear();
	LoadRoom(fn);
}

cItemList::~cItemList()
{
	items.clear();
}

void cItemList::Draw()
{
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		if (iter->getLive()) {
			glPushMatrix();
			if (iter->getId() > 1) {
				if (!iter->getRemoved()) {
					glTranslatef(step * (iter->getPlaceHolder() - 2), 0.0, 0.0); 
				} else {
					float x = iter->getXtarget();
					if (iter->getXslide() > x) {
						iter->setXslide(iter->getXslide() - iter->getXinc());
						glTranslatef(iter->getXslide(), 0.0, 0.0);
					} else
						if (iter->getXslide() <= iter->getXtarget()) {
							glTranslatef(step * (iter->getPlaceHolder() - 2), 0.0, 0.0); 
							iter->setRemoved(false);
						}
				}
			}
			iter->drawQuad(false); 
			glPopMatrix();
		}
		iter++;
	}
}

void cItemList::pickItem(const int hit)
{
	vector<cTexture>::iterator iter = items.begin();
	while (iter != items.end()) {
		if (iter->getId() == hit && iter->getLive()
			&& iter->getId() > 1 && iter < items.end()) {
			iter->setLive(false);
			while (iter != items.end()) {
				++iter;
				if (iter != items.end() && iter->getLive()) break;
			}
			while (iter != items.end()) {
				float x = (iter->getPlaceHolder()-2) * step - step;
				iter->setXslide((iter->getPlaceHolder()-2) * step);
				iter->setXtarget(x);
				iter->setRemoved(true);
				iter->setPlaceHolder(iter->getPlaceHolder() - 1);
				iter++;
			} 
			goto stop;
		}
		iter++;
	}
stop :
	int i = 0;//stuff
}