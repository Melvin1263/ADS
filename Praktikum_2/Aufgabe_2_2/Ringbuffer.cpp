#include "Ringbuffer.h"
#include <iostream>

Ringbuffer::Ringbuffer(int n)
{
    RingNode *first = nullptr;
    if(anker == nullptr)
    {
        anker = new RingNode();
        first = anker;
    }

    for (int i = 1, z=5; i<n; i++, z--)
    {
        RingNode* node = new RingNode();
        node->setAge(z);
        anker->next = node;
        anker = node;
    }

    // Ring schließen
    anker->next = first;
    anker = first;
    size = n;
}

Ringbuffer::~Ringbuffer()
{
}

bool Ringbuffer::addNode(const std::string description, const std::string data)
{
    RingNode* node = new RingNode();
    node->setAge(0);
    node->setDescription(description);
    node->setData(data);

    RingNode* tmp_next = anker->next->next;
    RingNode* tmp_oldest = anker->next;

    anker->next = node;
    node->next = tmp_next;
    anker = node;

    delete tmp_oldest;

    for(RingNode* pos = anker->next; pos->next != anker->next; pos = pos->next)
    {
        int oldAge = pos->getAge();
        pos->setAge(oldAge + 1);
    }

    return true;
}

RingNode * Ringbuffer::search(std::string search)
{
    RingNode* current = anker;

    for (int i = 0; i < size; i++)
    {
        if (current->getDescription().compare(search) == 0 
            || current->getData().compare(search) == 0)
            return current;

        current = current->next;
    };
    return nullptr;
}

void Ringbuffer::print()
{
    RingNode* current = anker;

    for(int i = 0; i < size; i++)
    {
        std::cout << "OldAge: " << current->getAge()
            << " Desc: " << current->getDescription()
            << " Data: " << current->getData() << std::endl;
        std::cout << "--------------------------" << std::endl;

        current = current->next;
    }
}
