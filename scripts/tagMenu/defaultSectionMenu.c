tagMenu: defaultSectionMenu
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"section" ]
Set Variable [ $$stopAddTagToCitation; Value:1 ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem; Value:TEMP::ksection ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “defaultSections” (ruleSection) ]
#
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ ruleSection::match; "section" ]
Perform Find [ ]
#
Sort Records [ Specified Sort Order: ruleSection::name; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ TEMP::ksection = ruleSection::ksection ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ TEMP::ksection ≠ ruleSection::ksection ]
Go to Record/Request/Page
[ First ]
End If
#
Set Variable [ $$stopAddTagToCitation ]
January 7, 平成26 16:15:33 Imagination Quality Management.fp7 - defaultSectionMenu -1-
