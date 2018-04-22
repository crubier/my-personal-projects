blob data:
	bloblo: number
	nono: text or symbol
	jojo: symbol

setos data:
	kiki: blob set list

coucou actor:
	keyboard: in
	display: out

model hoho:
	nonololol: coucou actor
	djdjdh: coucou actor
	main: truc interactor with nonololol as neuneu, 

truc interactor:
	muche1: bidule interactor with neuneu as nana
	muche2: bidule interactor with neuneu as nana
	muche3: machin interactor with neuneu as nini

	neuneu: coucou actor
	leuleu: coucou actor

	(layoutFlexVertical (layoutFlexHorizontal muche1, muche2),muche3) 

	(displayable to neuneu)

bidule interactor:
	nana : coucou actor
	lolo: number flow 
	(lolo from nana)
	coco : setos flow
	nounou: blob event
	(nounou to nana)
	(displayable to nana)

machin interactor:
	nini : coucou actor
	soso : symbol flow 
	(soso from nini.keyboard)
	(displayable to nini)

(displayable to a:actor) behavior:
	x : number flow
	(x to a.display)

	y : number flow 
	(y to a.display)

	z : number flow 
	(z to a.display)

	width : number flow
	(width to a.display)

	height: number flow
	(height to a.display)

(layoutFlexVertical elements:interactor list)
	(for all e in elements, e.height = )