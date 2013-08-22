function wantEventCallback()
{
	print("I want COOKIES!");
}
addGlobalEvent("wantEvent", wantEventCallback);

// calls event in Hello.lua
triggerGlobalEvent("testEvent");

