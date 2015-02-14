tagMenu: SortTags
#
#Sort records and save sort state for future visits.
If [ $$citationMatch = "key" and TEMP::sortKey = "abc" ]
Set Field [ TEMP::sortKey; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "node" and TEMP::sortNode = "abc" ]
Set Field [ TEMP::sortNode; "cat" ]
#Disabled this sort because the order lock puts the
#creator node when lock is active at bottom of list v
#in alpha order within category list.
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "medium" and TEMP::sortMedium = "abc" ]
Set Field [ TEMP::sortMedium; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "copyist" and TEMP::sortCopyist = "abc" ]
Set Field [ TEMP::sortCopyist; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "path" and TEMP::sortPath = "abc" ]
Set Field [ TEMP::sortPath; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "health" and TEMP::sortHealth = "abc" ]
Set Field [ TEMP::sortHealth; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "organ" and TEMP::sortOrgan = "abc" ]
Set Field [ TEMP::sortOrgan; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "sample" and TEMP::sortSample = "abc" ]
Set Field [ TEMP::sortSample; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "location" and TEMP::sortLocation = "abc" ]
Set Field [ TEMP::sortLocation; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "test" and TEMP::sortTest = "abc"
 or
Left ( Get ( LayoutName ) ; 4 ) = "test" and TEMP::sortTest = "abc" ]
Set Field [ TEMP::sortTest; "cat" ]
Sort Records [ Specified Sort Order: groupTest::order; based on value list: “order”
groupTest::name; ascending
tagMenus::orderOrLock; based on value list: “order”
test::order; ascending
test::testName; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "cite" and TEMP::sortCite = "abc" ]
Set Field [ TEMP::sortCite; "cat" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "ref" and TEMP::sortRef = "abc" ]
Set Field [ TEMP::sortRef; "cat" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "testItem" and TEMP::sortTestItem = "abc" ]
Set Field [ TEMP::sortTestItem; "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order”
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
Else If [ $$citationMatch = "node" ]
Set Field [ TEMP::sortNode; "abc" ]
Sort Records [ Specified Sort Order: ruleTagSectionName::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "medium" ]
Set Field [ TEMP::sortMedium; "abc" ]
Else If [ $$citationMatch = "copyist" ]
Set Field [ TEMP::sortCopyist; "abc" ]
Else If [ $$citationMatch = "path" ]
Set Field [ TEMP::sortPath; "abc" ]
Else If [ $$citationMatch = "health" ]
Set Field [ TEMP::sortHealth; "abc" ]
January 7, 平成26 16:25:50 Imagination Quality Management.fp7 - SortTags -1-tagMenu: SortTags
Else If [ $$citationMatch = "organ" ]
Set Field [ TEMP::sortOrgan; "abc" ]
Else If [ $$citationMatch = "sample" ]
Set Field [ TEMP::sortSample; "abc" ]
Else If [ $$citationMatch = "location" ]
Set Field [ TEMP::sortLocation; "abc" ]
Else If [ $$citationMatch = "testItem" ]
Set Field [ TEMP::sortTestItem; "abc" ]
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::name; ascending
test::testName; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "test"
 or
Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Set Field [ TEMP::sortTest; "abc" ]
Sort Records [ Specified Sort Order: test::testName; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "cite" ]
Set Field [ TEMP::sortCite; "abc" ]
Sort Records [ Specified Sort Order: reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
Else If [ $$citationMatch = "ref" ]
Set Field [ TEMP::sortRef; "abc" ]
Sort Records [ Specified Sort Order: reference::referenceShort; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
End If
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
January 7, 平成26 16:25:50 Imagination Quality Management.fp7 - SortTags -2-
