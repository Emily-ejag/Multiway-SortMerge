#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

//defines how many buffers are available in the Main Memory 
#define buffer_size 22

struct EmpRecord {
    int eid;
    string ename;
    int age;
    double salary;
};
EmpRecord buffers[buffer_size]; // this structure contains 22 buffers; available as your main memory.
EmpRecord buffers2[buffer_size];

// Grab a single block from the Emp.csv file, in theory if a block was larger than
// one tuple, this function would return an array of EmpRecords and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpRecord Grab_Emp_Record(fstream &empin) {
    string line, word;
    EmpRecord  emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}

//void Merge_Runs_in_Main_Memory(){
//    cout << "Merging Implemented" << endl;
//    return;
//} 

bool compare( EmpRecord a, EmpRecord b){
	if(a.eid < b.eid)
		return 1;
	else 
		return 0;
}

int getIndex(int array[], int size){
	int min;
	for(int i=0; i< size ;i++){
		min=array[i];
		if(min!= -1){
			break;
		}
	}
	
	int index = -2;
	for(int i=0; i< size ;i++){
		if(array[i] <= min & array[i] != -1){
		//	cout << "array[i-1] "<< array[i-1] << "array[i-1] "<< array[i] << "\n";
			min = array[i];
			index=i;
		}
	}
	//cout << "index"<< index;
	return index;
}

void Write_temp_file2(int cur_size, int num){
	
	// Create an output filestream object
	auto s = std::to_string(num);
	string name = "temp" + s + ".csv";
	cout <<"wrote temp file " << name <<endl;
    std::ofstream myFile(name);
    
    // Send data to the stream
    for (int i = 0; i < cur_size; i++)
    {
    	if(buffers2[i].eid!=0){
    		myFile << buffers2[i].eid << ","<< buffers2[i].ename << ","<< buffers2[i].age <<","<< buffers2[i].salary << "\n";
		}
		else{
			myFile << -1 << ","<< buffers2[i].ename << ","<< buffers2[i].age <<","<< buffers2[i].salary << "\n";
		}
        
    }
    
    // Close the file
    myFile.close();
    return;
}


void Write_temp_file(int cur_size, int num){
	
	// Create an output filestream object
	auto s = std::to_string(num);
	string name = "temp" + s + ".csv";
	cout <<"wrote temp file " << name <<endl;
    std::ofstream myFile(name);
    
    // Send data to the stream
    for (int i = 0; i < cur_size; i++)
    {
        myFile << buffers[i].eid << ","<< buffers[i].ename << ","<< buffers[i].age <<","<< buffers[i].salary << "\n";
    }
    
    // Close the file
    myFile.close();
    return;
}

void Print_Buffers(int cur_size) {
    for (int i = 0; i < cur_size; i++)
    {
        cout << i << " " << buffers[i].eid << " " << buffers[i].ename << " " << buffers[i].age << " " << buffers[i].salary << endl;
    }
}

//Sorting the buffers in main_memory based on 'eid' and storing the sorted records into a temporary file 
//You can change return type and arguments as you want. 
void Sort_in_Main_Memory(int num){
    cout << "Implementing Sorting" << endl;
	sort(buffers, buffers+buffer_size, compare);
	
	if(buffers[0].eid == -1){
		int nbuf=0;
		for(int i = 0; i < buffer_size; i++){
			if(buffers[i].eid != -1){
				buffers2[nbuf].eid = buffers[i].eid;
				buffers2[nbuf].age = buffers[i].age;
				buffers2[nbuf].ename = buffers[i].ename;
				buffers2[nbuf].salary = buffers[i].salary;	
				nbuf++;			
			}
		}
		Write_temp_file2(buffer_size, num);
	}else{
		Write_temp_file(buffer_size, num);
	}
	
	return;
}  

int main(){
  // open file streams to read and write
  fstream input_file;
  input_file.open("Emp.csv", ios::in);
 	
  // flags check when relations are done being read
  bool flag = true;
  int cur_size = 0;
  int num=0;
  int nlines=0;
  /*First Pass: The following loop will read each block put it into main_memory 
    and sort them then will put them into a temporary file for 2nd pass */
  while (flag) {
  	
      // FOR BLOCK IN RELATION EMP

      // grabs a block
      EmpRecord  single_EmpRecord  = Grab_Emp_Record(input_file);
      
      // checks if filestream is empty
      if (single_EmpRecord.eid == -1) {
        	flag = false;
      }else{
      	nlines++;
	  }
	  
	  if(cur_size + 1 > buffer_size || flag==false ){
	  	// to get just the ones left
	  	if(flag==false){
	  			  		
	  		for(int i=(nlines % buffer_size); i<buffer_size ; i++)
	  		buffers[i] = single_EmpRecord;
		}
	  	//memory is full now. Sort the blocks in Main Memory and Store it in a temporary file (runs)
          
          //cout << "Main Memory is full. Time to sort and store sorted blocks in a temporary file" << endl;
          //Print_Buffers(buffer_size);
          num++; 
          //SortMain("Attributes You Want");
          Sort_in_Main_Memory(num);
          //After sorting start again. Clearing memory and putting the current one into main memory.
          cur_size = 0;
          buffers[cur_size] = single_EmpRecord;
          cur_size += 1;

      }
      else{
          //Memory is not full store current record into buffers.
          buffers[cur_size] = single_EmpRecord ;
          cur_size += 1;
      }
     
  }
  
	input_file.close();
	bool flag_sorting_done = false;
	int array[num];
	int lines[num];
	int in;
	for (int j= 0; j<num;j++){
		lines[j] = 0;
	}
	
   /* Implement 2nd Pass: Read the temporary sorted files and utilize main_memory to store sorted runs into the EmpSorted.csv*/

  //Uncomment when you are ready to store the sorted relation
//  fstream sorted_file;  
//  sorted_file.open("EmpSorted.csv", ios::out | ios::app);
	fstream files[num];
	EmpRecord single_EmpRecord;
	//fstream files;
	for(int i=0; i < num; i++){
		auto s = std::to_string(i+1);
		string name = "temp" + s + ".csv";
  		files[i].open(name, ios::in);
	  	single_EmpRecord  = Grab_Emp_Record(files[i]);
	  	buffers[i] = single_EmpRecord ;
	  	array[i] = buffers[i].eid;
	  	//files.close();	
	}
	int count = 0;
	while(!flag_sorting_done){

		if(count > 0){
			int i=in;
			single_EmpRecord  = Grab_Emp_Record(files[i]);
			buffers[i] = single_EmpRecord;
			array[i] = buffers[i].eid;
		}	
		
		//Print_Buffers(num);
		in = getIndex(array, num);
		cout << "in file: " << in+1 <<endl;
		cout << "Start Merging" <<endl;
		
		if(in != -2){
			lines[in]= lines[in]+1;
			std::ofstream sorted_file;
			sorted_file.open("EmpSorted.csv", ios::out | ios::app);
			sorted_file << buffers[in].eid << ","<< buffers[in].ename << ","<< buffers[in].age <<","<< buffers[in].salary << "\n";
			sorted_file.close();}
		else{
			cout << "Merging finished"<< endl;
		}
	 	count++;
	}
	
	for(int i=0;i<num; i++){
		files[i].close();
		                 
	}
}
  