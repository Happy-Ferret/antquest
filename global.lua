gameName = "AntQuest"
defaultBg = "default.bmp"
inventoryBg = "inventorybg.bmp"
inventory = "inventory.bmp"
playerIcon = "personunanim.bmp"
speechBackground = "speech.bmp"

function gameStart ()
	addItem("Key", "key.gif")
	addItem("Watch", "watch.gif")
	addFrame(0,3,165,32,47, "walkLeft")
	addFrame(1,37,165,32,47, "walkLeft")
	addFrame(2,69,165,32,47, "walkLeft")
	addFrame(3,101,165,32,47, "walkLeft")
	addFrame(4,140,165,32,47, "walkLeft")
	addFrame(5,166,165,32,47, "walkLeft")
	addFrame(0,3,114,32,47, "walkRight")
	addFrame(1,37,114,32,47, "walkRight")
	addFrame(2,69,114,32,47, "walkRight")
	addFrame(3,101,114,32,47, "walkRight")
	addFrame(4,140,114,32,47, "walkRight")
	addFrame(5,166,114,32,47, "walkRight")
	addFrame(0,0,58,32,47, "stationaryDown")
	addFrame(1,0,58,32,47, "stationaryDown")
	addFrame(2,0,58,32,47, "stationaryDown")
	addFrame(3,0,58,32,47, "stationaryDown")
	addFrame(4,0,58,32,47, "stationaryDown")
	addFrame(5,0,58,32,47, "stationaryDown")
	loadRoom("room1.lua")
end

function itemKeyLook ()
	say("It's a key")
end

function defaultItemLook (item)
	say("It's a %item")
end

function defaultTalk()
	say("You can't talk to that")
end