backGround = "room1.bmp"
walkAreas = "room1WalkAreas.wlk"

function startRoom()
	addHotSpot(407, 244, 448, 328, "door1")
	enterScene(470,100)
	walkTo(400,100)
	say("hello")
	wait(1000)
	say("hello2")
	pickUp("Key")
	fadeOut(10)
end

function hsdoor1Use()
	if get("hsdoor1Open") then
		set("hsdoor1Open",false)
		say("It's open, I will close it.")	
	else 
		set("hsdoor1Open",true)
		say("It's closed, I will open it.")
	end
end

function hsdoor1Look()
	if hasItem("Key") then
		drop("Key")
		say("It's a door")
	else 
		say("It's locked")
	end
end

function defaultLook()
	say("There is nothing there")
end

function defaultUse()
	say("There is nothing there")
end
