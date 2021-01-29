BEGIN{
    old="[A-Z][a-z][a-z][0-9][0-9]"
    new="[0-9][0-9]:[0-9][0-9]"
}
/[a-z]{3}[0-9]{3}/{
    if(prev != $1)
    {
        print "User: " $1
        prev=$1
    }
    printf("\t  ");
    for(i=8;i<=NF;i++)
    {
        printf (" " $i);
    }
    printf("\n");
    stime=$5
    if(stime ~ old){
        earliest=stime
        earliestuid=$1
    }
    if(stime ~ new){
        latest=stime
        lateuid=$1
    }
}
{
    stime=$5
    curuid=$1
 
    if(stime ~ old && latest ~ new){
    }
    else if(stime ~ new && latest ~ old){
        latest = stime
        lateuid=curuid
        lateLine=$0
    }
    else if(stime ~ new && latest ~ new){
        if(latest < stime || (latest == stime && lateuid < curuid))
            latest = stime
            lateuid=curuid
            lateLine=$0
    }
    else if(stime ~ old && latest ~ old){
        stimemonth = stime
        stimeday = stime
        sub("[A-Z][a-z][a-z]","",stimeday)
        sub("[0-9][0-9]","",stimemonth)
        stimeconv=revmonths[stimemon] stimeday

        latestmoth = latest
        latestday = latest
        sub("[A-Z][a-z][a-z]","",latestday)
        sub("[0-9][0-9]","",latestmonth)
        latestconv=revmonths[latestmonth] latestday
        if(latestconv < stime || (latest == stime && lateuid < curuid))
            latest = stime
            lateuid=curuid
            lateLine=$0
    }

    if(stime ~ old && latest ~ new){
        earliest=stime
        earliestuid=curuid
        earliestLine=$0
    }
    else if(stime ~ new && latest ~ old){
    }
    else if(stime ~ new && latest ~ new){
        if(earliest < stime || (earliest == stime && earliestuid > curuid))
            earliest=stime
            earliest=curuid
            earliest=$0
    }
    else if(stime ~ old && latest ~ old){
        stimemonth = stime
        stimeday = stime
        sub("[A-Z][a-z][a-z]","",stimeday)
        sub("[0-9][0-9]","",stimemonth)
        stimeconv=revmonths[stimemon] stimeday

        earliestmoth=earliest
        earliestday=earliest
        sub("[A-Z][a-z][a-z]","",earliestday)
        sub("[0-9][0-9]","",earliestmonth)
        earliestconv=revmonths[earliestmonth] earliestday
        if(earliestconv < stime || (earliest == stime && earliestuid > curuid))
            earliest=stime
            earliestuid=curuid
            earliestLine=$0
    }

    monthnames = "Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec"
    split(monthnames,months,",")
    for(month in months){
        revmonths[months[month]]=month
    }
    printf ("\n");
}
END{
    
    print "Earliest Start Time:"
    print earliestLine

    printf("\n");

    print "Latest Start Time:"
    print lateLine
}
