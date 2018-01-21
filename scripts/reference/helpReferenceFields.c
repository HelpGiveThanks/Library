January 21, 2018 12:24:42 Library.fmp12 - helpReferenceFields -1-
reference: helpReferenceFields
#
#
#NOTE!!! IF future help fields need to be added,
#leave repition 50 blank as it is the one used on
#the reference layout. By leaving it blank, no
#text appears in this field.
#
#
#Get help message number from the object
#names: r33 = 33, and so on.
Set Variable [ $objectName; Value:Middle ( Get ( ActiveLayoutObjectName ) ; 2 ; 2 ) ]
Set Field [ TEMP::HelpMessage; TEMP::Help [$objectName] ]
Set Field [ TEMP::HelpRepetitionNumber; TextColor ( "help" ; RGB ( 150 ; 150 ; 150 ) ) & TextSize ( TextColor ( " #" ; RGB ( 150 ;
150 ; 150 ) ) ; 15 ) & Middle ( Get ( ActiveLayoutObjectName ) ; 2 ; 2 ) ]
Go to Field [ ]
#
#Get current window's width so view window
#can be moved the right of it.
Set Variable [ $width; Value:Get ( WindowWidth ) ]
#
#Closer this window just in case a copy of it
#is open, and then open a new one.
Close Window [ Name: "Reference Field Help"; Current file ]
#
#Open help message in a new window.
Set Variable [ $$stoploadCitation; Value:1 ]
New Window [ Name: "Reference Field Help"; Height: 431; Width: 331; Left: Case ( Get ( ScreenWidth ) > $width + 331 ; $width ; Get
( ScreenWidth ) - 331 ); Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
Go to Layout [ “ReferenceHelp” (reference) ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Set Variable [ $$stoploadCitation ]
#
