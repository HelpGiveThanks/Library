reference(citation): externalReferences
#
#If current mode is citation then use cite menu scirpt.
If [ $$citationMatch = "cite" ]
Perform Script [ “menuRefAddKeyWords” ]
Exit Script [ ]
End If
#
If [ $$ﬁndmode ≠ 1 ]
#Set testlearn internal reference ﬁeld conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Show all internal reference possibilities.
Go to Layout [ “learnMenu3Cite” (reference) ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Go to citation record's current selection or to ﬁrst record.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ FilterValues ( $$ref ; reference::_Lreference ) = reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ FilterValues ( $$ref ; reference::_Lreference ) ≠ reference::_Lreference & ¶ ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
End If
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
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
Else If [ $$ﬁndmode = 1 ]
#Set testlearn internal reference ﬁeld conditional
#formatting to transparent.
Set Variable [ $$internal ]
#
#Show all internal reference possibilities.
Go to Layout [ “learnFindCite” (reference) ]
End If
January 7, 平成26 17:39:47 Imagination Quality Management.fp7 - externalReferences -1-
