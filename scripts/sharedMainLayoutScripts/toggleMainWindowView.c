January 18, 2018 16:03:35 Library.fmp12 - toggleMainWindowView (update) -1-
sharedLayoutScripts: toggleMainWindowView (update)
#
#Reveal more or fewer pictures and links for tag.
#First toggle from current view to next view.
#Turn off loadRecord script to speed up process.
Set Variable [ $$stopLoadCitation; Value:1 ]
#
#from 0 to 1
If [ Right ( Get (LayoutName) ; 1) = 0
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn1” (testlearn) ]
Else
Go to Layout [ “learnStuff1” (testlearn) ]
End If
#
#from 1 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn2” (testlearn) ]
Else
Go to Layout [ “learnStuff2” (testlearn) ]
End If
#
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn3” (testlearn) ]
Else
Go to Layout [ “learnStuff3” (testlearn) ]
End If
#
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn4” (testlearn) ]
Else
Go to Layout [ “learnStuff4” (testlearn) ]
End If
#
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn5” (testlearn) ]
Else
Go to Layout [ “learnStuff5” (testlearn) ]
End If
#
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn4” (testlearn) ]
Else
Go to Layout [ “learnStuff4” (testlearn) ]
End If
#
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn3” (testlearn) ]
Else
Go to Layout [ “learnStuff3” (testlearn) ]
End If
#
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn2” (testlearn) ]
Else
Go to Layout [ “learnStuff2” (testlearn) ]
End If
#
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn1” (testlearn) ]
Else
Go to Layout [ “learnStuff1” (testlearn) ]
End If
#
#from 1 to 0
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn0” (testlearn) ]
Else
Go to Layout [ “learnStuff0” (testlearn) ]
End If
End If
#
#Remember layout user is on so they can be
#returned to correct view.
#Turn on loadRecord script needed for other scripts.
Set Variable [ $$stopLoadCitation ]
#
#from 0 to 1
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
#from 1 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
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
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutLmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutLmain; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
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
Set Field [ TEMP::layoutLmain; "less" & Get (LayoutName) ]
#from 1 to 0
Else If [ Right ( Get (LayoutName) ; 1) = 0
and
Left ( TEMP::layoutLmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
End If
#
#This scrolling step is affect brainstorm view
#when viewing brainstorm tags. Disabling it
#seems to accomplish what these two steps are
#supposed to do, which is keep selected record
#showing. Not sure why it was put in. Further
#testing is required before removing it, as in
#some contexts it might be required, in which
#case a sort just for brainstorm tags will need
#to be included as well.
// #Bring selected record to the top.
// Scroll Window
[ End ]
// Sort Records [ ]
[ No dialog ]
#
