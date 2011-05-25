function loadSpeech()
	addOption(1, "Give me money please")
	addOption(2, "Give me money")
	addOption(3, "Have some cheese")
	addOption(4, "Bye")
	say("Hey, how may I help you")
	optionEnable(2)
	optionEnable(4)
end

function chooseOption1() {
	say("You sir are still idiot")
	optionDisable(1)
	optionEnable(3)
}

function chooseOption2() {
	say("You sir are an idiot")
	optionEnable(1)
	optionDisable(2)
}

function chooseOption3() {
	say("Thanks, have a key")
	optionDisable(3)
}

function chooseOption4() {
	say("Bye")
	closeSpeech()
}