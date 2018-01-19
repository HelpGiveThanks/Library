tagMenu: newTag
Set Variable [ $library; Value:tagTable::ksection ]
Set Variable [ $rule; Value:tagTable::kGroupOrTest ]
New Record/Request
Set Field [ tagTable::ksection; $library ]
Set Field [ tagTable::kGroupOrTest; $rule ]
Go to Field [ tagTable::tag ]
January 7, 平成26 16:48:01 Imagination Quality Management.fp7 - newTag -1-
