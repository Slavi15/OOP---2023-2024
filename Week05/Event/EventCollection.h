#pragma once

#include "Event.h"

#define MAX_EVENTS_COUNT 20

class EventCollection
{
private:
	Event events[MAX_EVENTS_COUNT];
	size_t currentSize = 0;

	void insertionSort(const EventCollection& eventCollection, bool(*isLower)(const Event& e1, const Event& e2));

	EventCollection getEventsOnDate(const Date& date) const;

public:
	bool createEvent(const Event& event);
	bool removeEvent(const char* title);

	const int getEventByTitle(const char* title) const;
	const Event& getLongestEvent();

	EventCollection getMaxEvents(const Date& date);

	void print() const;
};