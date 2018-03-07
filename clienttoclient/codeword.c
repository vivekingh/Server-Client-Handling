void online(int cli){

	int i = 0;
	char temp[LEN],buf[LEN];
	strcpy(buf,"\0");
	snprintf(buf,LEN,"\nOnline friends: ");

	for(i=0;i<MAXIMUM;i++){
		if(fd[i]!=-1){
			snprintf(temp,LEN,"%d ",i);
				strcat(buf,temp);
		}
	}
	send(cli,buf,sizeof(buf),0);

}

void mineto(int cli){

	char buf[LEN];
	strcpy(buf,"\0");
	snprintf(buf,2,"%d",cli);
	send(cli,buf,sizeof(buf),0);

}
