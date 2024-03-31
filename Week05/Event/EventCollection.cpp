#include "EventCollection.h"

void EventCollection::insertionSort(const EventCollection& eventCollection, bool(*isLower)(const Event& e1, const Event& e2))
{
	for (size_t i = 0; i < currentSize - 1; i++)
	{
		size_t minIndex = i;

		for (size_t j = i + 1; j < currentSize; j++)
			if (isLower(eventCollection.events[j], eventCollection.events[minIndex]))
				minIndex = j;

		if (minIndex != i)
			std::swap(events[i], events[minIndex]);
	}
}

EventCollection EventCollection::getEventsOnDate(const Date& date) const
{
	EventCollection eventCollection;

	for (size_t i = 0; i < currentSize; i++)
		if (compareDates(events[i].getDate(), date) == 0)
		{
			eventCollection.createEvent(events[i]);
			eventCollection.currentSize++;
		}

	return eventCollection;
}

bool EventCollection::createEvent(const Event& event)
{
	if (currentSize >= MAX_EVENTS_COUNT) return false;

	events[currentSize++] = event;
	return true;
}

bool EventCollection::removeEvent(const char* title)
{
	if (!title) return false;

	int index = getEventByTitle(title);

	if (index == -1) return false;

	std::swap(events[index], events[currentSize--]);
	return true;
}

const int EventCollection::getEventByTitle(const char* title) const
{
	if (!title) return -1;

	for (int i = 0; i < currentSize; i++)
		if (strcmp(events[i].getTitle(), title) == 0)
			return i;

	return -1;
}

const Event& EventCollection::getLongestEvent()
{
	insertionSort(*this, [](const Event& e1, const Event& e2) -> bool { 
		return (e1.getEndTime().getTime() - e1.getStartTime().getTime()) < (e2.getEndTime().getTime() - e2.getStartTime().getTime()); 
	});

	return events[currentSize - 1];
}

EventCollection EventCollection::getMaxEvents(const Date& date)
{
	EventCollection eventsOnDate = getEventsOnDate(date);

	insertionSort(eventsOnDate, [](const Event& e1, const Event& e2) -> bool { return compareTimes(e1.getEndTime(), e2.getEndTime()) == -1; });

	EventCollection toReturn;
	toReturn.createEvent(eventsOnDate.events[0]);

	for (size_t i = 1; i < eventsOnDate.currentSize; i++)
		if (compareTimes(toReturn.events[toReturn.currentSize - 1].getEndTime(), eventsOnDate.events[i].getStartTime()) <= 0)
			toReturn.createEvent(eventsOnDate.events[i]);

	return toReturn;
}

void EventCollection::print() const
{
	for (size_t i = 0; i < currentSize; i++)
		events[i].printEvent();
}