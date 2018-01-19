January 15, 2018 16:22:39 Library.fmp12 - reviewPrimaryNodeCopyright -1-
tagMenu: reviewPrimaryNodeCopyright
#
#
#Might not be in use. Testing required before deleting.
#
#
#Stop record loading scripts.
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Closer this window just in case a copy of it
#is open, and then open a new one.
Close Window [ Name: "Copyright"; Current file ]
New Window [ Name: "Copyright"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#
#Start record loading scripts.
Set Variable [ $$stopTest ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Essential to show user a copyright versus test
#item lock message when this script is triggered
#informUserHowToEditLockedLayoutText.
Set Variable [ $$showCopyrightLockMessage; Value:1 ]
#
#
