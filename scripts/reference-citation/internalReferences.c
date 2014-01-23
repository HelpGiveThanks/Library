reference(citation): internalReferences
#
If [ $$ﬁndmode ≠ 1 ]
#Set testlearn internal reference ﬁeld conditional
#formatting to green if there are any.
Set Variable [ $$internal; Value:1 ]
#
#Show all internal reference possibilities.
Go to Layout [ “learnMenu4RefCite” (testlearn) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#If the user has yet to create any Learn or internal records
#let them know, and return user to outside reference records.
If [ Get (LastError) = 401 ]
Perform Script [ “externalReferences” ]
Show Custom Dialog [ Message: "No inside (Learn) records have been created."; Buttons: “OK” ]
End If
#
#Continue with show all internal reference possibilities...
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$cite and $$citationMatch = "cite" or
testlearn::_Ltestlearn & "¶" = FilterValues ( $$ref ; testlearn::_Ltestlearn & "¶" ) and $$citationMatch = "ref" ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Decided below was too much help. User can look
#on main screen to see where cite or reference is located.
// #Capture information about location of ref and cite records.
// #Because it can be in four possible locations, conditonal
// #formatting is essential to help user remember.
// If [ testlearn::_Ltestlearn = $$citationitem and $$citationMatch = "cite" ]
// #
// #Turn on cite location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$citeIsLearnRecord; Value:1 ]
// #
// Else If [ testlearn::_Ltestlearn & "¶" = FilterValues ( $$ref ; testlearn::_Ltestlearn & "¶" ) and $$citationMatch = "ref" ]
// #
// #Turn on reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsLearnRecord; Value:1 ]
// End If
#
#If no records are used as a cite or ref, go to ﬁrst record.
If [ Get (LastError) = 101 ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
// #Turn on reference location variable that conditionally
// #formatts buttons to tell user where reference is located.
// Set Variable [ $$refIsLearnRecord ]
End If
#
#Update conditional formatting in main window.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#If in ﬁnd mode ...
Else If [ $$ﬁndmode = 1 ]
#Set testlearn internal reference ﬁeld conditional
#formatting to green if there are any.
Set Variable [ $$internal; Value:1 ]
#
#Show all internal reference possibilities.
Go to Layout [ “learnMenu4RefCiteFindTL” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Perform Find [ ]
End If
January 7, 平成26 17:39:16 Imagination Quality Management.fp7 - internalReferences -1-
