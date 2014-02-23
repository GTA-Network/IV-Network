function wantEventCallback()
{
	print("I want COOKIES!");
}
addGlobalEvent("wantEvent", wantEventCallback);

// calls event in Hello.lua
triggerGlobalEvent("testEvent");

function onPlayerChat(text, player)
{
	sendMessageToAll(player.getName()+"("+player.getId()+"): "+text, 0xFFFFFF, true);
}

addEvent("playerChat", onPlayerChat);