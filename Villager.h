#ifndef DRAGONS_LAIR_VILLAGER_H
#define DRAGONS_LAIR_VILLAGER_H
#include "Object.h"
#include "Entity.h"
#include "List.h"
class Hunter;
class Villager : public Entity {
private:
    List<Object*> shop;
    string dialog;
public:
    Villager(string, string);
    ~Villager();
    void addItem(Object*);
    void sell(Hunter*, int);
    void showShop() const;
    void describe() const override;
};

#endif //DRAGONS_LAIR_VILLAGER_H