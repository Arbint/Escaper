// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

void ADoor::OnTriggered(AActor* actor)
{
	ActorsInTrigger++;
	SetDoorOpen(true);
}

void ADoor::OnActorLeftTrigger(AActor* actor)
{
	ActorsInTrigger--;
	if (ActorsInTrigger == 0)
	{
		SetDoorOpen(false);
	}
}
