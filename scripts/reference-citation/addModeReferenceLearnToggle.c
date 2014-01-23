reference(citation): addModeReferenceLearnToggle
If [ Get (WindowName) = "References" ]
Go to Layout [ <unknown> ]
Set Window Title [ Current Window; New Title: "Learn" ]
Else If [ Get (WindowName) = "Learn" ]
Go to Layout [ “ReferenceAddToTag” (reference) ]
Set Window Title [ Current Window; New Title: "References" ]
End If
January 7, 平成26 17:41:32 Imagination Quality Management.fp7 - addModeReferenceLearnToggle -1-
