
; ============ Cleanup ============
#>>screen -S $myscreen -X stuff 'exit\015'
>>rm $SCREENLOG
>screen -r $myscreen
>>^A
>h
<hardcopy
>exit
>mv hardcopy.0 $SCREENLOG
>
