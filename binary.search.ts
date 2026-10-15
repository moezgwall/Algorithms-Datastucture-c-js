
/* target : value looked for in the array 
 * arr    : buffer that holds the values 
 * compare: cb for different types (numbers,string,objects)
 * */
function binarySearch<T>(target:T,arr: readonly T[],compare: (a:T,b:T) => number){
        let low = 0;
        let high = arr.length - 1;

        while (low <= high){
                const mid = low + Math.floor((high-low)/2);
                const value = arr[mid] as T; 
                const ret = compare(value,target);
                if (ret === 0) return mid; 
                if (ret < 0){
                        low = mid + 1;
                }else{
                        high = mid - 1;
                }
        }
        return -1;
}


