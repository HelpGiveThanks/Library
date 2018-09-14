August 30, 2018 12:34:01 Library.fmp12 - viewReference -1-
reference: viewReference
#
#Exit RefDump field if user is in it.
Go to Field [ ]
#
#Get current window's width so view window
#can be moved the right of it.
Set Variable [ $width; Value:Get ( WindowWidth ) ]
#
#Close this window just in case a copy of it
#is open, and then open a new one.
Close Window [ Name: "View Reference"; Current file ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stoploadCitation; Value:1 ]
New Window [ Name: "View Reference"; Height: 431; Width: 331; Left: Case ( Get ( ScreenWidth ) > $width + 331 ; $width ; Get
( ScreenWidth ) - 331 ); Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize:
“Yes” ]
#
#
If [ Get (LayoutName) ≠ "referenceEdit" ]
Set Variable [ $$hideReferenceButtons; Value:1 ]
End If
#
#Show just the record of interest.
Go to Layout [ “ReferenceViewEDIT” (reference) ]
Set Zoom Level [ 100%; Camera: Back; Resolution: Full ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stoploadCitation ]
Refresh Window
Set Variable [ $$hideReferenceButtons ]
#
// #Prevent the user doing anything else until
// #they leave this window.
// Pause/Resume Script [ Indefinitely ]
#
