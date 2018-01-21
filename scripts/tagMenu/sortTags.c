January 19, 2018 14:37:24 Library.fmp12 - sortTags -1-
tagMenu: sortTags
#
#Sort records and save sort state for future visits.
If [ $$citationMatch = "key" and TEMP::sortKey = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Field [ TEMP::sortKey; "cat" ]
Exit Script [ ]
#
Else If [ $$citationMatch = "node" and TEMP::sortNode = "abc" ]
Set Field [ TEMP::sortNode; "cat" ]
#Disabled this sort because the order lock puts the
#creator node when lock is active at bottom of list
#in alpha order within category list.
// Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "medium" and TEMP::sortMedium = "abc" ]
Set Field [ TEMP::sortMedium; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "publisher" and TEMP::sortPublisher = "abc" ]
Set Field [ TEMP::sortPublisher; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "path" and TEMP::sortPath = "abc" ]
Set Field [ TEMP::sortPath; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "copyright" and TEMP::sortCopyright = "abc" ]
Set Field [ TEMP::sortCopyright; "cat" ]
#
#Sort to group, textstyle, and then tag,
#so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::name; ascending
tagMenus::textStyleOrCreatorNodeFlag; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "publication" and TEMP::sortPublication = "abc" ]
Set Field [ TEMP::sortPublication; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "brainstorm" and TEMP::sortBrainstorm = "abc" ]
Set Field [ TEMP::sortBrainstorm; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "testSection" and TEMP::sortTestSection = "abc" ]
Set Field [ TEMP::sortTestSection; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "testSubsection" and TEMP::sortTestSubsection = "abc"
 or
Left ( Get ( LayoutName ) ; 4 ) = "test" and TEMP::sortTestSubsection = "abc" ]
Set Field [ TEMP::sortTestSubsection; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
testSubsectionTemplate::order; ascending
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "cite" and TEMP::sortCite = "abc" ]
Set Field [ TEMP::sortCite; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "ref" and TEMP::sortRef = "abc" ]
Set Field [ TEMP::sortRef; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list: “order
Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "testItem" and TEMP::sortTestItem = "abc" ]
Set Field [ TEMP::sortTestItem; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value
list: “order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
End If
#
#
#
#Sort records and save sort state for future visits.
If [ $$citationMatch = "key" ]
Set Field [ TEMP::sortKey; "abc" ]
#
Else If [ $$citationMatch = "node" ]
Set Field [ TEMP::sortNode; "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "medium" ]
Set Field [ TEMP::sortMedium; "abc" ]
#
Else If [ $$citationMatch = "publisher" ]
Set Field [ TEMP::sortPublisher; "abc" ]
#
Else If [ $$citationMatch = "path" ]
Set Field [ TEMP::sortPath; "abc" ]
#
Else If [ $$citationMatch = "copyright" ]
Set Field [ TEMP::sortCopyright; "abc" ]
#
Else If [ $$citationMatch = "publication" ]
Set Field [ TEMP::sortPublication; "abc" ]
#
Else If [ $$citationMatch = "brainstorm" ]
Set Field [ TEMP::sortBrainstorm; "abc" ]
#
Else If [ $$citationMatch = "testSection" ]
Set Field [ TEMP::sortTestSection; "abc" ]
#
Else If [ $$citationMatch = "testItem" ]
Set Field [ TEMP::sortTestItem; "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "test"
 or
Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Set Field [ TEMP::sortTestSubsection; "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "cite" ]
Set Field [ TEMP::sortCite; "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
#
Else If [ $$citationMatch = "ref" ]
Set Field [ TEMP::sortRef; "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
End If
#
#Sort records.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
