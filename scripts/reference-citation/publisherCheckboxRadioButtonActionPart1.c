reference(citation): PublisherCheckboxRadioButtonActionPart1
If [ ValueCount ( reference::publisherTypeAlternative ) = 2 ]
Set Field [ reference::publisherTypeAlternative; Substitute ( reference::publisherTypeAlternative ; GetValue (reference::publisherTypeAlternative;1 ) & "¶" ; "" ) ]
End If
Go to Field [ ]
January 7, 平成26 18:00:08 Imagination Quality Management.fp7 - PublisherCheckboxRadioButtonActionPart1 -1-
