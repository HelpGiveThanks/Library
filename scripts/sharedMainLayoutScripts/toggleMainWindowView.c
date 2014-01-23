sharedMainLayoutScripts: ToggleMainWindowView
#
#Reveal more or fewer pictures and links for tag.
#First toggle from current view to next view.
#Turn off loadRecord script to speed up process.
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Go to Layout [ “learn2” (testlearn) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Go to Layout [ “learn3” (testlearn) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Go to Layout [ “learn4” (testlearn) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Go to Layout [ “learn3” (testlearn) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Go to Layout [ “learn2” (testlearn) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Go to Layout [ “learn1” (testlearn) ]
End If
#
#Remember layout user is on so they can be
#returned to correct view.
#Turn on loadRecord script needed for other scripts.
Set Variable [ $$stopLoadCitation ]
#
#from 1 to 2
If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutLmain; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutLmain; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutLmain; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
End If
#
January 7, 平成26 18:06:56 Imagination Quality Management.fp7 - ToggleMainWindowView -1-
