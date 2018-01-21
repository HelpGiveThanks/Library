January 21, 2018 12:19:23 Library.fmp12 - addModeReferenceLearnToggle -1-
reference: addModeReferenceLearnToggle
If [ Get (WindowName) = "References" ]
Go to Layout [ <unknown> ]
Set Window Title [ Current Window; New Title: "Learn" ]
Else If [ Get (WindowName) = "Learn" ]
Go to Layout [ “ReferenceAddToTag” (reference) ]
Set Window Title [ Current Window; New Title: "References" ]
End If
