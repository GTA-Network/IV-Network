function testEventCallback()
	print("I like COOKIES!");

-- calls event in Hello.nut
	triggerGlobalEvent("wantEvent")
end

function resourceEventCallback()
	print("Just a local resource event!")
end


function main()
	local inst = createEntity("VEHICLE")
	inst:setPosition(1.0, 2.0, 3.0)
	triggerEvent("resourceEvent")
	print("Script started")
end

addEvent("resourceEvent", resourceEventCallback)
addGlobalEvent("testEvent", testEventCallback)
main()
