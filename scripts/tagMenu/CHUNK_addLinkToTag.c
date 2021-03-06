January 20, 2018 17:58:54 Library.fmp12 - CHUNK_addLinkToTag -1-
tagMenu: CHUNK_addLinkToTag
#
#Get key for link that is to be added to tag.
If [ Get ( LayoutTableName ) = "reference" ]
Set Variable [ $tag; Value:reference::_Lreference ]
Set Variable [ $number; Value:$$number ]
Set Variable [ $$number ]
Set Variable [ $name; Value:$$name ]
Set Variable [ $$name ]
Set Variable [ $window; Value:Get (WindowName) ]
Else If [ Get ( LayoutTableName ) = "testlearn" ]
Set Variable [ $tag; Value:testlearn::_Ltestlearn ]
Set Variable [ $number; Value:$$number ]
Set Variable [ $$number ]
Set Variable [ $name; Value:$$name ]
Set Variable [ $$name ]
Set Variable [ $window; Value:Get (WindowName) ]
End If
#
#Now add all the added record’s node and keyword
#tags to any newly added sections.
Perform Script [ “CHUNKaddReferenceNodeAndKeywordTagIDs” ]
#
#Complete process of adding link to tag.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Leave field so user can see
#conditional formatting.
Go to Field [ ]
#
#Remove key from other slots in may be in, to
#prevent duplicates showing up.
If [ tagMenus::Ktitle1 = $tag and $number ≠ 1 ]
Set Field [ tagMenus::Ktitle1; "" ]
Else If [ tagMenus::Ktitle2 = $tag and $number ≠ 2 ]
Set Field [ tagMenus::Ktitle2; "" ]
Else If [ tagMenus::Ktitle3= $tag and $number ≠ 3 ]
Set Field [ tagMenus::Ktitle3; "" ]
End If
#
#Place key in selected slot.
If [ tagMenus::Ktitle1 ≠ $tag and $number = 1 ]
Set Field [ tagMenus::Ktitle1; $tag ]
Select Window [ Name: $window; Current file ]
Exit Script [ ]
Else If [ tagMenus::Ktitle2 ≠ $tag and $number = 2 ]
Set Field [ tagMenus::Ktitle2; $tag ]
Select Window [ Name: $window; Current file ]
Exit Script [ ]
Else If [ tagMenus::Ktitle3 ≠ $tag and $number = 3 ]
Set Field [ tagMenus::Ktitle3; $tag ]
Select Window [ Name: $window; Current file ]
Exit Script [ ]
End If
#
#Remove it key if it is already in use.
If [ tagMenus::Ktitle1 = $tag and $number = 1 ]
Set Field [ tagMenus::Ktitle1; "" ]
Else If [ tagMenus::Ktitle2 = $tag and $number = 2 ]
Set Field [ tagMenus::Ktitle2; "" ]
Else If [ tagMenus::Ktitle3 = $tag and $number = 3 ]
Set Field [ tagMenus::Ktitle3; "" ]
End If
Select Window [ Name: $window; Current file ]
