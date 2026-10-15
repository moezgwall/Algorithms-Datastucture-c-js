// let suppose that we have a window of size= K 
// we will sum each chunk(size=k) elements 
// and get the max sum possible of consecutive k elements 

function maxSumOfKelements(arr: number[],k:number):number{
        if (k < 0 || k >= arr.length){
                return 0;
        }
        let sum = 0;
        for (let i=0; i<k;i++){
            sum+= arr[i] as number;
        }
        let best = sum; 
        for(let i=k; i < arr.length;i++){
                sum += arr[i] as number;
                sum -= arr[i-k] as number;
                best = Math.max(best,sum);
        }
        return best;
}

const arr = [2,1,5,1,3,2];
console.log(maxSumOfKelements(arr, 4));

