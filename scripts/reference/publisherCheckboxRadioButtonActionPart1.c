January 21, 2018 12:22:42 Library.fmp12 - publisherCheckboxRadioButtonActionPart1 -1-
reference: publisherCheckboxRadioButtonActionPart1
#
If [ ValueCount ( reference::publisherTypeAlternative ) = 2 ]
Set Field [ reference::publisherTypeAlternative; Substitute ( reference::publisherTypeAlternative ; GetValue (reference::
publisherTypeAlternative;1 ) & "¶" ; "" ) ]
End If
Go to Field [ ]
#
