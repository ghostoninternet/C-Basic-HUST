#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NhanVien
{
      int ID;
      int *status;
      int *second;
      int *minute;
      int *hour;
} NV;

void TongThoiGianLamViec(NV EMPLOYEES[], int employeesID[], int frequency[], int num_employees)
{
      /*
      Hàm TongThoiGianLamViec:
      1. Quy đổi thời gian ra giây để tính toán và lưu các kết quả vào một mảng tong_thoi_gian[num_employees]
      2. Sắp xếp mảng đó theo thứ tự từ lớn đến bé, đồng thời sắp xếp mảng employeesID vì 2 mảng song song nhau
      3. Lấy ID của employeesID[0]
      */
      int tong_thoi_gian[num_employees];
      for (int i = 0; i < num_employees; i++)
      {
            tong_thoi_gian[i] = 0;
            for (int j = 1; j < frequency[i]; j += 2)
            {
                  tong_thoi_gian[i] = +((EMPLOYEES[i].hour[j] * 60 * 60 + EMPLOYEES[i].minute[j] * 60 + EMPLOYEES[i].second[j]) - (EMPLOYEES[i].hour[j - 1] * 60 * 60 + EMPLOYEES[i].minute[j - 1] * 60 + EMPLOYEES[i].second[j - 1]));
            }
      }

      int time_temp, ID_temp;
      for (int i = 0; i < num_employees - 1; i++)
      {
            for (int j = i; j < num_employees; j++)
            {
                  if (tong_thoi_gian[j] > tong_thoi_gian[i])
                  {
                        time_temp = tong_thoi_gian[j];
                        tong_thoi_gian[j] = tong_thoi_gian[i];
                        tong_thoi_gian[i] = time_temp;

                        ID_temp = employeesID[j];
                        employeesID[j] = employeesID[i];
                        employeesID[i] = ID_temp;
                  }
            }
      }
      printf("Nguoi o trong phong lau nhat la: %d\n", employeesID[0]);
}

void NguoiVeSomNhat(NV EMPLOYEES[], int frequency[], int num_employees)
{
      /*
      Hàm tìm người về sớm nhất.
      1. Lưu trữ ID của nhân viên ra một mảng khác tên employeesID[num_employees(số lượng nhân viên đi làm)]
      2. Sử dụng mảng timeStamp_OUT[num_employees] để lưu trữ các mốc thời gian đi về của nhân viên tính theo đơn vị giây
      3. Sắp xếp mảng timeStamp_OUT từ lớn đến bé song song với mảng employeesID.
      4. Lấy phần tử đầu tiên của mảng employeesID làm kết quả nhân viên về sớm nhất.
      */
      int timeStamp_OUT[num_employees];
      int employeesID[num_employees];
      for (int i = 0; i < num_employees; i++)
      {
            employeesID[i] = EMPLOYEES[i].ID;
      }

      for (int i = 0; i < num_employees; i++)
      {
            for (int j = frequency[i] - 1; j >= 0; j--)
            {
                  if (EMPLOYEES[i].status[j] == 1)
                  {
                        timeStamp_OUT[i] = EMPLOYEES[i].hour[j - 1] * 60 * 60 + EMPLOYEES[i].minute[j - 1] * 60 + EMPLOYEES[i].second[j - 1];
                        break;
                  }
                  else
                  {
                        timeStamp_OUT[i] = EMPLOYEES[i].hour[j] * 60 * 60 + EMPLOYEES[i].minute[j] * 60 + EMPLOYEES[i].second[j];
                        break;
                  }
            }
      }
      int time_temp, ID_temp;
      for (int i = 0; i < num_employees - 1; i++)
      {
            for (int j = i; j < num_employees; j++)
            {
                  if (timeStamp_OUT[j] < timeStamp_OUT[i])
                  {
                        time_temp = timeStamp_OUT[j];
                        timeStamp_OUT[j] = timeStamp_OUT[i];
                        timeStamp_OUT[i] = time_temp;

                        ID_temp = employeesID[j];
                        employeesID[j] = employeesID[i];
                        employeesID[i] = ID_temp;
                  }
            }
      }
      printf("Nguoi ve som nhat la: %d\n", employeesID[0]);
}

void NguoiViPham(NV EMPLOYEES[], int frequency[], int num_employees)
{
      /*
      Hàm tìm người vi phạm về mặt thời gian
      1. Các biến timeIN_MORNING, timeOUT_MORNING, timeIN_AFTERNOON, timeOUT_AFTERNOON lần lượt là các biến để lưu trữ mốc thời gian
      đi làm sáng, đi về sáng, đi làm chiều, đi về chiều theo đơn vị giây
      2. Mảng marked[4] dùng để đánh dấu mốc thời gian:
            - Lần đầu tới công ty vào sáng
            - Lần cuối rời công ty vào sáng
            - Lần đầu tới công ty vào chiều
            - Lần cuối rời công ty vào chiều
      */
      int timeIN_MORNING = 8 * 60 * 60 + 30 * 60;
      int timeOUT_MORNING = 12 * 60 * 60;
      int timeIN_AFTERNOON = 13 * 60 * 60 + 30 * 60;
      int timeOUT_AFTERNOON = 17 * 60 * 60;

      int timeIN;  // Lưu trữ thời gian đến
      int timeOUT; // Lưu trữ thời gian rời đi

      int marked[4];
      for (int i = 0; i < 4; i++)
      {
            marked[i] = 0;
      }

      for (int i = 0; i < num_employees; i++)
      {
            /*
            Ở đây vì đầu vào đầu tiên của file log sẽ là thời gian đến công ty vào sáng sớm nên lưu luôn mốc thời gian đó vào biến timeIN
            Sẽ có 2 trường hợp, người đó lần đầu đến vào sáng và người đó lần đầu đến vào chiều
            */
            timeIN = EMPLOYEES[i].hour[0] * 60 * 60 + EMPLOYEES[i].minute[0] * 60 + EMPLOYEES[i].second[0];
            if (timeIN > timeIN_MORNING)
            {
                  printf("Nhan vien %d den muon sang\n", EMPLOYEES[i].ID);
                  marked[0] = 1;
            }
            else if (timeIN > timeIN_AFTERNOON)
            {
                  printf("Nhan vien %d den muon chieu\n", EMPLOYEES[i].ID);
                  marked[2] = 1;
            }
            /*
            Vòng lặp qua các mốc thời gian của một ID
            Việc cho j đi từ dưới lên sẽ đảm bảo lấy được lần cuối cùng rời công ty mà không lo việc bị nhầm giữa "ra công ty do có việc" hay "rời công ty về nhà"
            Nếu gặp status = 1 thì status trước đó sẽ là 0, nên phải có j - 1, ngược lại nếu status = 0 thì tính trực tiếp luôn mốc thời gian tại đó và lưu vào biến timeOUT
            */
            for (int j = frequency[i] - 1; j >= 0; j--)
            {
                  if (EMPLOYEES[i].status[j] == 1)
                  {
                        timeOUT = EMPLOYEES[i].hour[j - 1] * 60 * 60 + EMPLOYEES[i].minute[j - 1] * 60 + EMPLOYEES[i].second[j - 1];
                        if (timeOUT >= timeOUT_MORNING && timeOUT < timeIN_AFTERNOON) // Nếu thời gian ra lớn hơn thời gian ra sáng và bé hơn thời gian vào chiều --> Về đúng
                        {
                              marked[1] = 1;
                        }
                        if (timeOUT < timeOUT_MORNING && marked[1] == 0) // Nếu thời gian ra bé hơn thời gian ra sáng và marked[1] chưa được ghi nhận --> Về sớm
                        {
                              printf("Nhan vien %d ve som buoi sang\n", EMPLOYEES[i].ID);
                              marked[1] = 1;
                        }
                        if (timeOUT >= timeOUT_AFTERNOON) // Nếu thời gian ra lớn hơn bằng thời gian ra chiều --> Về đúng giờ
                        {
                              marked[3] = 1;
                        }
                        if (timeOUT < timeOUT_AFTERNOON && marked[3] == 0) // Nếu thời gian ra bé hơn thời gian ra chiều và marked[3] chưa được ghi nhận --> Về sớm
                        {
                              printf("Nhan vien %d ve som buoi chieu\n", EMPLOYEES[i].ID);
                              marked[3] = 1;
                        }
                  }
                  else
                  {
                        timeOUT = EMPLOYEES[i].hour[j] * 60 * 60 + EMPLOYEES[i].minute[j] * 60 + EMPLOYEES[i].second[j];
                        if (timeOUT >= timeOUT_MORNING && timeOUT < timeIN_AFTERNOON) // Nếu thời gian ra lớn hơn thời gian ra sáng và bé hơn thời gian vào chiều --> Về đúng giờ
                        {
                              marked[1] = 1; // Ghi nhận
                        }
                        if (timeOUT < timeOUT_MORNING && marked[1] == 0) // Nếu thời gian ra bé hơn thời gian ra sáng và marked[1] chưa được ghi nhận --> Về sớm
                        {
                              printf("Nhan vien %d ve som buoi sang\n", EMPLOYEES[i].ID);
                              marked[1] = 1;
                        }
                        if (timeOUT >= timeOUT_AFTERNOON) // Nếu thời gian ra lớn hơn bằng thời gian ra chiều --> Về đúng giờ
                        {
                              marked[3] = 1;
                        }
                        if (timeOUT < timeOUT_AFTERNOON && marked[3] == 0) // Nếu thời gian ra bé hơn thời gian ra chiều và marked[3] chưa được ghi nhận --> Về sớm
                        {
                              printf("Nhan vien %d ve som buoi chieu\n", EMPLOYEES[i].ID);
                              marked[3] = 1;
                        }
                  }
            }
            for (int k = 0; k < frequency[i]; k++)
            {
                  if (EMPLOYEES[i].status[k] == 1)
                  {
                        timeIN = EMPLOYEES[i].hour[k] * 60 * 60 + EMPLOYEES[i].minute[k] * 60 + EMPLOYEES[i].second[k];
                        if (timeIN > timeOUT_MORNING && timeIN <= timeIN_AFTERNOON)
                        {
                              marked[2] = 1;
                        }
                        if (timeIN > timeIN_AFTERNOON && marked[2] == 0)
                        {
                              marked[2] = 1;
                              printf("Nhan vien %d den muon buoi chieu\n", EMPLOYEES[i].ID);
                        }
                  }
            }
            // Reset lại các giá trị của marked[4]
            for (int i = 0; i < 4; i++)
            {
                  marked[i] = 0;
            }
      }
}

int main()
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Log File 4.txt";
      FILE *LOG;
      if ((LOG = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.");
            exit(1);
      }

      // Đếm số dòng có trong file
      int line_counting = 0;
      char word[90];
      while (fgets(word, 90, LOG) != 0)
      {
            line_counting++;
      }
      fseek(LOG, 0, SEEK_SET);

      // Lưu trữ các ID có trong file vào một mảng có kích cỡ = số dòng trong file
      int ID_Line[line_counting - 1]; // có -1 do line_counting sẽ bị thừa 1 dòng
      int index = 0;                  // đánh dấu index cho mảng ID_Line
      do
      {
            fscanf(LOG, "%d", &ID_Line[index]);
            fgets(word, 90, LOG);
            index++;
      } while (feof(LOG) == 0);

      //Đếm số lượng ID khác nhau có trong mảng ID_Line --> Số lượng nhân viên đi làm hôm đó.
      int ID_diff = 1;
      // Sắp xếp để tiện cho việc duyệt mảng
      int temp;
      for (int i = 0; i < line_counting - 2; i++)
      {
            for (int j = i; j < line_counting - 1; j++)
            {
                  if (ID_Line[i] > ID_Line[j])
                  {
                        temp = ID_Line[i];
                        ID_Line[i] = ID_Line[j];
                        ID_Line[j] = temp;
                  }
            }
      }

      for (int i = 0; i < line_counting - 2; i++) //Đếm số lượng ID khác nhau
      {
            if (ID_Line[i] != ID_Line[i + 1])
            {
                  ID_diff++;
            }
      }
      /*
      Lưu trữ các ID vào mảng employee_ID với kích cỡ là ID_diff (Số lượng nhân viên) và các phần tử trong mảng sẽ là các ID của nhân viên
      Mảng này khác với ID_Line ở 2 điểm:
      1. Mảng employee_ID này có kích cỡ nhỏ hơn nhiều.
      2. Mảng employee_ID chỉ gồm các phần tử riêng biệt là các ID của nhân viên.
      */
      int employee_ID[ID_diff];
      int index_employee_ID = 0;
      for (int i = 0; i < line_counting - 1; i++)
      {
            if (ID_Line[i] != ID_Line[i + 1])
            {
                  employee_ID[index_employee_ID] = ID_Line[i];
                  index_employee_ID++;
            }
      }
      printf("Number of current employees: %d\n", ID_diff);
      fseek(LOG, 0, SEEK_SET); // Reset lại cursor về vị trí đầu tiên ở trong file để chuẩn bị cho lần duyệt tiếp theo.

      /*
      Lưu trữ dữ liệu từ file vào trong chương trình
      1. Chương trình tạo Structure kiểu NV vào khai báo mảngMPLOYEES với kích cỡ = ID_diff (Số lượng ID khác nhau)
      2. Trong Structure NV có các con trỏ, nên để có thể cấp phát động, cần phải đếm số lần một nhân viên xuất hiện và lưu vào mảng employees_appear_freq[ID_diff]
      để dùng lượng đó cấp phát động cho các con trỏ.
      */
      NV EMPLOYEES[ID_diff];
      int sum_second = 0;
      for (int i = 0; i < ID_diff; i++)
      {
            EMPLOYEES[i].ID = employee_ID[i];
      }
      int employees_appear_freq[ID_diff];
      int current_ID;
      for (int i = 0; i < ID_diff; i++)
      {
            employees_appear_freq[i] = 0;
            while (fscanf(LOG, "%d", &current_ID) != EOF)
            {
                  if (EMPLOYEES[i].ID == current_ID)
                  {
                        employees_appear_freq[i]++;
                  }
                  fgets(word, 90, LOG);
            }
            fseek(LOG, 0, SEEK_SET);
      }
      for (int i = 0; i < ID_diff; i++)
      {
            printf("%d %d\n", EMPLOYEES[i].ID, employees_appear_freq[i]);
      }

      /*
      3. Chương trình bắt đầu việc duyệt qua từng phần tử của EMPLOYEES
      4. Tại mỗi phần tử của EMPLOYEES:
            - Cấp phát động dựa với kích cỡ = số lần nhân viên đó xuất hiện
            - Lặp qua file, tại mỗi ID tương ứng với ID hiện tại có trong EMPLOYEES bắt đầu quá trình đưa dữ liệu từ trong file vào tương ứng với trường của EMPLOYEES.
      */
      char status[4];
      int hour, minute, second;
      int info_index = 0;
      for (int i = 0; i < ID_diff; i++)
      {
            EMPLOYEES[i].status = (int *)malloc(sizeof(int) * employees_appear_freq[i]);
            EMPLOYEES[i].hour = (int *)malloc(sizeof(int) * employees_appear_freq[i]);
            EMPLOYEES[i].minute = (int *)malloc(sizeof(int) * employees_appear_freq[i]);
            EMPLOYEES[i].second = (int *)malloc(sizeof(int) * employees_appear_freq[i]);

            while (fscanf(LOG, "%d %s %d:%d:%d", &current_ID, status, &hour, &minute, &second) != EOF)
            {
                  if (EMPLOYEES[i].ID == current_ID)
                  {
                        if (strcmp(status, "IN") == 0)
                        {
                              EMPLOYEES[i].status[info_index] = 1;
                        }
                        else
                        {
                              EMPLOYEES[i].status[info_index] = 0;
                        }
                        EMPLOYEES[i].hour[info_index] = hour;
                        EMPLOYEES[i].minute[info_index] = minute;
                        EMPLOYEES[i].second[info_index] = second;
                        info_index++;
                  }
            }
            info_index = 0;
            fseek(LOG, 0, SEEK_SET);
      }
      // In ra thông tin của mỗi nhân viên
      for (int i = 0; i < ID_diff; i++)
      {
            printf("ID: %d\n", EMPLOYEES[i].ID);
            for (int j = 0; j < employees_appear_freq[i]; j++)
            {
                  printf("Status: %d  Time: %d:%d:%d\n", EMPLOYEES[i].status[j], EMPLOYEES[i].hour[j], EMPLOYEES[i].minute[j], EMPLOYEES[i].second[j]);
            }
            printf("\n");
      }
      fclose(LOG);

      TongThoiGianLamViec(EMPLOYEES, employee_ID, employees_appear_freq, ID_diff); // Tìm nhân viên có thời gian làm việc lâu nhất
      NguoiVeSomNhat(EMPLOYEES, employees_appear_freq, ID_diff);                   // Tìm người về sớm nhất
      NguoiViPham(EMPLOYEES, employees_appear_freq, ID_diff);                      // Tìm nhân viên vi phạm thời gian (đi sớm về muộn)
      return 0;
}