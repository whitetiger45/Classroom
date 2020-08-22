one possible solution to the keygen_practice challenge.
task: Simple keygen practice. You can patch, however the main goal is to find at least 50 valid keys. Have fun!

(note: this solution may not be optimal, but it will generate 9! good keys, above and beyond the challenge's expectations.)

1. compile work.cc
2. compile permutation.cc
3. run bash command:
while(true); do round="$(./work)";
  if [[ $round =~ "try" ]]; 
  then 
    key="$(echo $round | awk '{print $2}')";
    status="$(./license $key)";
    if [[ $status =~ "Good" ]]; 
    then 
      ./perm $key >> keys;
      echo -e "good key $key and its permutations written to file."; 
      break;
    fi;
  fi; 
  sleep 1; 
done
4. less -r keys

