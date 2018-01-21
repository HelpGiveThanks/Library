January 15, 2018 15:24:43 Library.fmp12 - toggleTestWindowView -1-
test: test: toggleTestWindowView
#
#Reveal more or fewer pictures and links for tag.
#First toggle from current view to next view.
#Turn off loadRecord script to speed up process.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#from 0 to 1
If [ Right ( Get (LayoutName) ; 1) = 0
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult1” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED1” (testlearn) ]
End If
#
#from 1 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult2” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED2” (testlearn) ]
End If
#
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult3” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED3” (testlearn) ]
End If
#
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult4” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED4” (testlearn) ]
End If
#
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult5” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED5” (testlearn) ]
End If
#
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult4” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED4” (testlearn) ]
End If
#
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult3” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED3” (testlearn) ]
End If
#
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult2” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED2” (testlearn) ]
End If
#
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult1” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED1” (testlearn) ]
End If
#
#from 1 to 0
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
If [ TEMP::testSubjectNodeIsLocked = ""
 and
TEMP::primaryNodeIsLocked = "" ]
Go to Layout [ “testResult0” (testlearn) ]
Else
Go to Layout [ “testResultLOCKED0” (testlearn) ]
End If
End If
#
#Remember layout user is on so they can be
#returned to correct view.
#
#Turn on loadRecord script needed for other scripts.
Set Variable [ $$stopLoadTestRecord ]
#
#from 0 to 1
If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutTmain; "more" & Get (LayoutName) ]
#from 1 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutTmain; "more" & Get (LayoutName) ]
#from 2 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutTmain; "more" & Get (LayoutName) ]
#from 3 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutTmain; "more" & Get (LayoutName) ]
#from 4 to 5
Else If [ Right ( Get (LayoutName) ; 1) = 5
and
Left ( TEMP::layoutTmain ; 4 ) = "more" ]
Set Field [ TEMP::layoutTmain; "less" & Get (LayoutName) ]
#from 5 to 4
Else If [ Right ( Get (LayoutName) ; 1) = 4
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutTmain; "less" & Get (LayoutName) ]
#from 4 to 3
Else If [ Right ( Get (LayoutName) ; 1) = 3
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutTmain; "less" & Get (LayoutName) ]
#from 3 to 2
Else If [ Right ( Get (LayoutName) ; 1) = 2
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutTmain; "less" & Get (LayoutName) ]
#from 2 to 1
Else If [ Right ( Get (LayoutName) ; 1) = 1
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutTmain; "less" & Get (LayoutName) ]
#from 1 to 0
Else If [ Right ( Get (LayoutName) ; 1) = 0
and
Left ( TEMP::layoutTmain ; 4 ) = "less" ]
Set Field [ TEMP::layoutTmain; "more" & Get (LayoutName) ]
End If
#
#
